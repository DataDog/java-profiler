---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 09:51:40 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 10 |
| Allocations | 137 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 11 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1793630792 42
1793630797 42
1793630802 42
1793630807 43
1793630812 43
1793630817 43
1793630822 43
1793630827 43
1793630832 43
1793630837 43
1793630842 43
1793630847 48
1793630852 48
1793630857 48
1793630862 48
1793630867 48
1793630872 48
1793630877 48
1793630882 48
1793630887 48
```
</details>

---

