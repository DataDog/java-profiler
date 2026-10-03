---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-03 05:48:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 10 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 198 |
| Sample Rate | 3.30/sec |
| Health Score | 206% |
| Threads | 13 |
| Allocations | 126 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1791020609 40
1791020614 40
1791020619 40
1791020624 40
1791020629 40
1791020634 40
1791020639 40
1791020644 40
1791020649 40
1791020654 40
1791020659 40
1791020664 40
1791020669 40
1791020674 40
1791020679 40
1791020684 40
1791020689 40
1791020694 40
1791020699 40
1791020704 40
```
</details>

---

