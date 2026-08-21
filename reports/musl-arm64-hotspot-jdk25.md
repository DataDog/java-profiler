---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-21 19:10:10 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 12 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 37 |
| Sample Rate | 0.62/sec |
| Health Score | 39% |
| Threads | 12 |
| Allocations | 27 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1787353567 29
1787353572 29
1787353577 29
1787353582 29
1787353587 29
1787353592 29
1787353597 29
1787353602 29
1787353607 29
1787353612 29
1787353617 29
1787353622 29
1787353627 29
1787353632 29
1787353637 24
1787353642 24
1787353647 24
1787353652 24
1787353657 24
1787353662 24
```
</details>

---

