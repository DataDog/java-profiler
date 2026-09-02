---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-02 09:19:24 EDT

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1788354658 94
1788354663 94
1788354668 96
1788354673 96
1788354678 96
1788354683 96
1788354688 96
1788354693 96
1788354698 96
1788354703 96
1788354708 96
1788354713 96
1788354718 96
1788354723 96
1788354728 96
1788354733 96
1788354738 96
1788354743 96
1788354748 96
1788354753 96
```
</details>

---

