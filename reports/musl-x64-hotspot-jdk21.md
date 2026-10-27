---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 09:26:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 827 |
| Sample Rate | 13.78/sec |
| Health Score | 861% |
| Threads | 12 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 67-75 cores)</summary>

```
1793107208 67
1793107213 67
1793107218 67
1793107223 67
1793107228 67
1793107233 67
1793107238 75
1793107243 75
1793107248 75
1793107253 75
1793107258 75
1793107263 75
1793107268 75
1793107273 75
1793107278 75
1793107283 75
1793107288 75
1793107293 75
1793107298 75
1793107303 75
```
</details>

---

