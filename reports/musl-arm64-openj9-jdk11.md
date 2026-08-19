---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-19 05:17:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 7 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 924 |
| Sample Rate | 15.40/sec |
| Health Score | 962% |
| Threads | 9 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787130742 64
1787130747 64
1787130752 64
1787130757 64
1787130762 64
1787130767 64
1787130772 64
1787130777 64
1787130782 64
1787130787 64
1787130792 64
1787130797 64
1787130802 64
1787130807 64
1787130812 64
1787130817 64
1787130822 64
1787130827 64
1787130832 64
1787130837 64
```
</details>

---

