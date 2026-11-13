---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 13:50:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 10 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (3 unique values: 37-46 cores)</summary>

```
1794595526 37
1794595531 40
1794595536 40
1794595541 40
1794595546 40
1794595551 40
1794595556 40
1794595561 40
1794595566 40
1794595571 40
1794595576 40
1794595581 40
1794595586 40
1794595591 40
1794595596 46
1794595601 46
1794595606 46
1794595611 46
1794595616 46
1794595621 46
```
</details>

---

