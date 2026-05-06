---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-06 08:18:45 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 9 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (5 unique values: 50-58 cores)</summary>

```
1778069710 54
1778069715 54
1778069720 54
1778069725 58
1778069730 58
1778069735 58
1778069740 58
1778069745 58
1778069750 54
1778069755 54
1778069760 52
1778069765 52
1778069770 54
1778069775 54
1778069780 54
1778069785 50
1778069791 50
1778069796 50
1778069801 50
1778069806 50
```
</details>

---

