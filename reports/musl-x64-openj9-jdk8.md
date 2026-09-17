---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-17 19:15:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 95 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 433 |
| Sample Rate | 7.22/sec |
| Health Score | 451% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 95-96 cores)</summary>

```
1789686638 96
1789686643 96
1789686648 96
1789686653 96
1789686658 96
1789686663 96
1789686668 96
1789686673 96
1789686678 96
1789686683 96
1789686688 96
1789686693 96
1789686698 96
1789686703 96
1789686708 96
1789686713 96
1789686718 96
1789686723 96
1789686728 96
1789686733 95
```
</details>

---

