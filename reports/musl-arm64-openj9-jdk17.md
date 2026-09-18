---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 02:29:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 201 |
| Sample Rate | 3.35/sec |
| Health Score | 209% |
| Threads | 10 |
| Allocations | 129 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1789712797 43
1789712802 43
1789712807 48
1789712812 48
1789712817 48
1789712822 48
1789712827 48
1789712832 48
1789712837 48
1789712842 48
1789712847 48
1789712852 48
1789712857 48
1789712862 48
1789712867 48
1789712872 48
1789712877 48
1789712882 48
1789712887 48
1789712892 48
```
</details>

---

