---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-12 05:49:53 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 12.53/sec |
| Health Score | 783% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (4 unique values: 32-37 cores)</summary>

```
1778579145 36
1778579150 36
1778579155 32
1778579160 32
1778579165 32
1778579170 32
1778579175 32
1778579180 32
1778579185 32
1778579190 32
1778579195 32
1778579200 32
1778579205 37
1778579210 37
1778579215 37
1778579220 37
1778579225 37
1778579230 37
1778579235 37
1778579240 37
```
</details>

---

