---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 14:53:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (4 unique values: 71-79 cores)</summary>

```
1795636169 74
1795636174 74
1795636179 74
1795636184 74
1795636189 74
1795636194 74
1795636199 74
1795636204 74
1795636209 74
1795636214 79
1795636219 79
1795636224 79
1795636229 79
1795636234 79
1795636239 79
1795636244 79
1795636249 76
1795636254 76
1795636259 71
1795636264 71
```
</details>

---

