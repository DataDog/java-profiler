---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-12 09:14:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 7 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 9 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1791810624 48
1791810629 48
1791810634 36
1791810639 36
1791810644 36
1791810649 36
1791810654 36
1791810659 36
1791810664 36
1791810669 36
1791810674 36
1791810679 36
1791810684 36
1791810689 36
1791810694 36
1791810699 36
1791810704 36
1791810709 36
1791810715 36
1791810720 36
```
</details>

---

