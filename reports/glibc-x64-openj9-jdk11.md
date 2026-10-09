---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-09 07:06:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 337 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 689 |
| Sample Rate | 11.48/sec |
| Health Score | 718% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (2 unique values: 24-32 cores)</summary>

```
1791543717 24
1791543722 24
1791543727 32
1791543732 32
1791543737 32
1791543742 32
1791543747 32
1791543752 32
1791543757 32
1791543762 32
1791543767 32
1791543772 32
1791543777 32
1791543782 32
1791543787 32
1791543792 32
1791543797 32
1791543802 32
1791543807 32
1791543812 32
```
</details>

---

