---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-24 05:24:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790241534 48
1790241539 48
1790241544 43
1790241549 43
1790241554 43
1790241559 43
1790241564 38
1790241569 38
1790241574 38
1790241579 38
1790241584 38
1790241589 38
1790241595 38
1790241600 38
1790241605 38
1790241610 43
1790241615 43
1790241620 43
1790241625 43
1790241630 43
```
</details>

---

