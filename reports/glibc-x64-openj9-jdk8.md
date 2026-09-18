---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-18 09:29:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1789737757 60
1789737762 60
1789737767 60
1789737772 60
1789737777 60
1789737782 60
1789737787 60
1789737792 60
1789737797 60
1789737802 60
1789737807 64
1789737812 64
1789737817 64
1789737822 64
1789737827 64
1789737832 64
1789737837 64
1789737842 64
1789737847 64
1789737852 64
```
</details>

---

