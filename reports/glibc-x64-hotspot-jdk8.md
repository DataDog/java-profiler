---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-22 13:05:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 163 |
| Sample Rate | 2.72/sec |
| Health Score | 170% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 47-51 cores)</summary>

```
1787418092 51
1787418097 51
1787418102 51
1787418107 51
1787418112 47
1787418117 47
1787418122 47
1787418127 47
1787418132 47
1787418137 47
1787418142 47
1787418147 49
1787418152 49
1787418157 49
1787418162 49
1787418167 49
1787418172 51
1787418177 51
1787418182 51
1787418187 51
```
</details>

---

