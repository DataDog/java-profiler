---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 05:28:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1790241529 43
1790241534 38
1790241539 38
1790241544 38
1790241549 38
1790241554 38
1790241559 38
1790241564 38
1790241569 38
1790241574 38
1790241579 38
1790241584 38
1790241589 38
1790241594 38
1790241600 38
1790241605 38
1790241610 43
1790241615 43
1790241620 43
1790241625 43
```
</details>

---

