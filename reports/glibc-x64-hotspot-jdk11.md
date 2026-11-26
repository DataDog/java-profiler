---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 16:09:01 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 11 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 36-69 cores)</summary>

```
1795727093 36
1795727098 36
1795727103 69
1795727108 69
1795727113 69
1795727118 69
1795727123 69
1795727128 69
1795727133 69
1795727138 69
1795727143 69
1795727148 69
1795727153 69
1795727158 69
1795727163 69
1795727168 69
1795727173 69
1795727178 69
1795727183 69
1795727188 69
```
</details>

---

