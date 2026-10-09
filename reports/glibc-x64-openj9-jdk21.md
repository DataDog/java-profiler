---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-09 06:38:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 824 |
| Sample Rate | 13.73/sec |
| Health Score | 858% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1791541873 48
1791541878 48
1791541883 48
1791541888 48
1791541893 48
1791541898 48
1791541903 48
1791541908 48
1791541913 46
1791541918 46
1791541923 44
1791541928 44
1791541933 44
1791541938 44
1791541943 44
1791541948 44
1791541953 44
1791541958 44
1791541963 42
1791541968 42
```
</details>

---

