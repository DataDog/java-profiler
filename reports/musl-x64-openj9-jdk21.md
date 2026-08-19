---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-19 05:17:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 10 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1121 |
| Sample Rate | 18.68/sec |
| Health Score | 1168% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 76-96 cores)</summary>

```
1787130777 96
1787130782 96
1787130787 96
1787130792 96
1787130797 96
1787130802 96
1787130807 96
1787130812 96
1787130817 96
1787130822 96
1787130827 96
1787130832 96
1787130837 96
1787130842 96
1787130847 96
1787130852 96
1787130857 96
1787130862 76
1787130867 76
1787130872 76
```
</details>

---

