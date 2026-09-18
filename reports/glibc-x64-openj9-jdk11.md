---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 02:31:39 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1134 |
| Sample Rate | 18.90/sec |
| Health Score | 1181% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 92-96 cores)</summary>

```
1789712751 92
1789712756 92
1789712761 92
1789712766 92
1789712772 92
1789712777 92
1789712782 92
1789712787 92
1789712792 92
1789712797 92
1789712802 92
1789712807 92
1789712812 92
1789712817 92
1789712822 92
1789712827 96
1789712832 96
1789712837 96
1789712842 96
1789712847 96
```
</details>

---

