---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-27 09:40:19 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 734 |
| Sample Rate | 12.23/sec |
| Health Score | 764% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 86-96 cores)</summary>

```
1787837733 96
1787837738 96
1787837743 88
1787837748 88
1787837753 88
1787837758 88
1787837763 88
1787837768 88
1787837773 88
1787837778 88
1787837783 88
1787837788 88
1787837793 88
1787837798 88
1787837803 88
1787837808 88
1787837813 88
1787837818 88
1787837823 86
1787837828 86
```
</details>

---

