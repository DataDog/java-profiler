---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-20 12:18:19 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 815 |
| Sample Rate | 13.58/sec |
| Health Score | 849% |
| Threads | 9 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1792512747 32
1792512752 32
1792512757 32
1792512762 32
1792512767 32
1792512772 32
1792512777 32
1792512782 32
1792512787 32
1792512792 32
1792512797 32
1792512802 32
1792512807 32
1792512812 32
1792512817 32
1792512822 32
1792512827 32
1792512832 32
1792512837 32
1792512842 32
```
</details>

---

