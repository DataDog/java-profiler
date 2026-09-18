---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 03:41:22 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 14 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1789716638 25
1789716643 25
1789716648 30
1789716653 30
1789716658 30
1789716663 30
1789716668 30
1789716673 30
1789716678 30
1789716683 30
1789716688 30
1789716693 30
1789716698 30
1789716703 30
1789716708 30
1789716713 30
1789716718 30
1789716723 30
1789716728 30
1789716733 30
```
</details>

---

