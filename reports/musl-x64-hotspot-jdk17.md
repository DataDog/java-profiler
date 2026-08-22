---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-22 15:27:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 46-66 cores)</summary>

```
1787426581 46
1787426586 46
1787426591 46
1787426596 46
1787426601 46
1787426606 46
1787426611 66
1787426616 66
1787426621 66
1787426626 66
1787426631 66
1787426636 66
1787426641 66
1787426646 66
1787426651 66
1787426656 66
1787426661 66
1787426666 66
1787426671 66
1787426676 66
```
</details>

---

