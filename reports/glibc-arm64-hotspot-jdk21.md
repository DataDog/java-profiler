---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 08:54:44 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 214 |
| Sample Rate | 3.57/sec |
| Health Score | 223% |
| Threads | 14 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1793800188 47
1793800193 47
1793800198 48
1793800203 48
1793800208 48
1793800213 48
1793800218 48
1793800224 48
1793800229 48
1793800234 48
1793800239 48
1793800244 48
1793800249 48
1793800254 48
1793800259 48
1793800264 48
1793800269 43
1793800274 43
1793800279 43
1793800284 43
```
</details>

---

