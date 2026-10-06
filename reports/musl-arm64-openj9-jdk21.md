---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-06 11:23:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 7 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791299918 48
1791299923 48
1791299928 48
1791299933 48
1791299938 48
1791299943 48
1791299948 48
1791299953 48
1791299958 48
1791299963 43
1791299968 43
1791299973 43
1791299978 43
1791299983 43
1791299988 43
1791299993 43
1791299998 43
1791300003 43
1791300008 43
1791300013 43
```
</details>

---

