---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 09:27:48 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 10 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1789737747 48
1789737752 48
1789737757 48
1789737762 48
1789737767 48
1789737772 48
1789737777 48
1789737782 48
1789737787 48
1789737792 48
1789737797 48
1789737802 48
1789737807 48
1789737812 48
1789737817 48
1789737822 48
1789737827 48
1789737832 48
1789737837 48
1789737842 48
```
</details>

---

