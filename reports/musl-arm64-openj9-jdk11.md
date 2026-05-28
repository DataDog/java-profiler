---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-28 11:27:29 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 53-55 cores)</summary>

```
1779981654 53
1779981659 53
1779981664 53
1779981669 53
1779981674 53
1779981679 53
1779981684 53
1779981689 53
1779981694 53
1779981699 53
1779981704 53
1779981709 53
1779981714 53
1779981719 53
1779981724 53
1779981729 53
1779981734 53
1779981739 53
1779981744 53
1779981749 53
```
</details>

---

