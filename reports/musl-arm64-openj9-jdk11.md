---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-06 11:23:38 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 311 |
| Sample Rate | 5.18/sec |
| Health Score | 324% |
| Threads | 9 |
| Allocations | 140 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (4 unique values: 42-48 cores)</summary>

```
1791299900 48
1791299905 48
1791299910 48
1791299915 48
1791299920 48
1791299925 48
1791299930 48
1791299935 48
1791299940 48
1791299945 48
1791299950 48
1791299955 47
1791299960 47
1791299965 47
1791299970 47
1791299975 47
1791299980 42
1791299985 42
1791299990 42
1791299995 42
```
</details>

---

