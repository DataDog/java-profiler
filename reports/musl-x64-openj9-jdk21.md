---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 08:20:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 521 |
| Sample Rate | 8.68/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (4 unique values: 21-29 cores)</summary>

```
1770124654 29
1770124659 26
1770124664 26
1770124669 26
1770124674 25
1770124679 25
1770124684 25
1770124689 25
1770124694 21
1770124699 21
1770124704 21
1770124709 21
1770124714 21
1770124719 21
1770124724 21
1770124729 21
1770124734 21
1770124739 21
1770124744 21
1770124749 21
```
</details>

---

