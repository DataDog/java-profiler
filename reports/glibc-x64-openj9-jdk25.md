---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-21 12:26:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1792599653 74
1792599658 74
1792599663 74
1792599668 74
1792599673 74
1792599678 74
1792599683 74
1792599688 74
1792599693 74
1792599698 74
1792599703 74
1792599708 74
1792599713 76
1792599718 76
1792599723 76
1792599728 76
1792599733 76
1792599738 76
1792599743 76
1792599748 76
```
</details>

---

