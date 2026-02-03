---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 05:39:38 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 11 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 900 |
| Sample Rate | 15.00/sec |
| Health Score | 938% |
| Threads | 13 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (6 unique values: 40-64 cores)</summary>

```
1770114747 40
1770114752 55
1770114757 55
1770114762 55
1770114767 55
1770114772 55
1770114777 55
1770114782 55
1770114787 55
1770114792 55
1770114797 55
1770114802 55
1770114807 55
1770114812 55
1770114817 55
1770114822 55
1770114827 55
1770114832 55
1770114837 55
1770114842 64
```
</details>

---

