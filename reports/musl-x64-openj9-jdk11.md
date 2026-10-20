---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 13:05:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1004 |
| Sample Rate | 16.73/sec |
| Health Score | 1046% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (4 unique values: 82-91 cores)</summary>

```
1792515648 82
1792515653 82
1792515658 84
1792515663 84
1792515668 84
1792515673 89
1792515678 89
1792515683 89
1792515688 89
1792515693 89
1792515698 89
1792515703 89
1792515708 89
1792515713 89
1792515718 91
1792515723 91
1792515728 91
1792515733 91
1792515738 91
1792515743 91
```
</details>

---

