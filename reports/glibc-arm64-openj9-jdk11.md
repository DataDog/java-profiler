---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-03 05:48:21 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 113 |
| Sample Rate | 1.88/sec |
| Health Score | 117% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 41 |
| Sample Rate | 0.68/sec |
| Health Score | 42% |
| Threads | 10 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1791020589 24
1791020594 24
1791020599 24
1791020604 24
1791020609 24
1791020614 29
1791020619 29
1791020624 29
1791020629 29
1791020634 29
1791020639 29
1791020644 29
1791020649 29
1791020654 29
1791020659 29
1791020664 29
1791020669 29
1791020674 29
1791020679 29
1791020684 29
```
</details>

---

