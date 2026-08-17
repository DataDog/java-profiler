---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-17 05:46:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1786959757 48
1786959762 48
1786959767 48
1786959772 48
1786959777 48
1786959782 48
1786959787 48
1786959792 48
1786959797 48
1786959802 43
1786959807 43
1786959812 42
1786959817 42
1786959822 42
1786959827 42
1786959832 42
1786959837 42
1786959842 42
1786959847 42
1786959852 47
```
</details>

---

