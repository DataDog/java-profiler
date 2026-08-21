---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-21 03:04:25 EDT

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
| CPU Cores (start) | 76 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 945 |
| Sample Rate | 15.75/sec |
| Health Score | 984% |
| Threads | 10 |
| Allocations | 536 |

<details>
<summary>CPU Timeline (3 unique values: 76-81 cores)</summary>

```
1787295634 76
1787295639 81
1787295644 81
1787295649 81
1787295654 81
1787295659 81
1787295664 81
1787295669 81
1787295674 81
1787295679 81
1787295684 81
1787295689 81
1787295694 81
1787295699 81
1787295704 81
1787295709 81
1787295714 81
1787295719 81
1787295724 81
1787295729 81
```
</details>

---

