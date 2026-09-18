---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 09:32:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 14 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 22-40 cores)</summary>

```
1789737757 40
1789737762 40
1789737767 40
1789737772 40
1789737777 40
1789737782 40
1789737787 40
1789737792 22
1789737797 22
1789737802 22
1789737807 22
1789737812 22
1789737817 22
1789737822 22
1789737827 22
1789737832 22
1789737837 22
1789737842 22
1789737847 22
1789737852 22
```
</details>

---

