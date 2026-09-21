---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 09:57:55 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1789998779 32
1789998784 32
1789998789 32
1789998794 32
1789998799 32
1789998804 32
1789998809 32
1789998814 32
1789998819 32
1789998824 32
1789998829 32
1789998834 32
1789998839 32
1789998844 32
1789998849 32
1789998854 32
1789998859 32
1789998864 32
1789998869 32
1789998874 32
```
</details>

---

