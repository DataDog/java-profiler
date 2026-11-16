---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 05:18:23 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 382 |
| Sample Rate | 6.37/sec |
| Health Score | 398% |
| Threads | 11 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794823878 48
1794823883 48
1794823888 48
1794823893 48
1794823898 48
1794823903 48
1794823908 48
1794823913 48
1794823918 48
1794823923 48
1794823928 48
1794823933 48
1794823938 48
1794823943 48
1794823948 48
1794823953 48
1794823958 48
1794823963 48
1794823968 48
1794823973 48
```
</details>

---

