---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-09 07:07:02 EDT

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 211 |
| Sample Rate | 3.52/sec |
| Health Score | 220% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 74-88 cores)</summary>

```
1791543742 86
1791543747 86
1791543752 86
1791543757 86
1791543762 86
1791543767 86
1791543772 86
1791543777 86
1791543782 88
1791543787 88
1791543792 88
1791543797 76
1791543802 76
1791543807 76
1791543812 76
1791543817 76
1791543822 76
1791543827 74
1791543832 74
1791543837 74
```
</details>

---

