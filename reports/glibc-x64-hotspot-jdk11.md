---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-30 05:49:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 657 |
| Sample Rate | 10.95/sec |
| Health Score | 684% |
| Threads | 10 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1788083071 81
1788083076 81
1788083081 81
1788083086 81
1788083091 81
1788083096 81
1788083101 81
1788083107 81
1788083112 81
1788083117 81
1788083122 81
1788083127 81
1788083132 81
1788083137 81
1788083142 81
1788083147 81
1788083152 81
1788083157 81
1788083162 81
1788083167 79
```
</details>

---

