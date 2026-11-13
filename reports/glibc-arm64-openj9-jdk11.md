---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:19:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794582893 48
1794582898 48
1794582903 48
1794582908 48
1794582913 48
1794582918 48
1794582923 48
1794582928 48
1794582933 48
1794582938 48
1794582943 48
1794582948 48
1794582953 48
1794582958 48
1794582963 48
1794582968 48
1794582973 48
1794582978 48
1794582983 48
1794582988 48
```
</details>

---

