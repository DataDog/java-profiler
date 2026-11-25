---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 14:53:13 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 8 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (5 unique values: 48-85 cores)</summary>

```
1795636174 85
1795636179 85
1795636184 76
1795636189 76
1795636194 78
1795636199 78
1795636204 50
1795636209 50
1795636214 50
1795636219 50
1795636224 50
1795636229 50
1795636234 50
1795636239 50
1795636244 50
1795636249 50
1795636254 50
1795636259 50
1795636264 50
1795636269 50
```
</details>

---

