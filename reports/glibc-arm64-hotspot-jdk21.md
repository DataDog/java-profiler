---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-05 19:52:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 10 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 14 |
| Allocations | 91 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793926159 40
1793926164 40
1793926169 40
1793926174 40
1793926179 40
1793926184 40
1793926189 40
1793926194 40
1793926199 40
1793926204 40
1793926209 40
1793926214 40
1793926219 40
1793926224 40
1793926229 40
1793926234 40
1793926239 40
1793926245 40
1793926250 40
1793926255 40
```
</details>

---

