---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 06:36:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 8 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 26-51 cores)</summary>

```
1795001531 26
1795001536 26
1795001541 26
1795001546 26
1795001551 26
1795001556 26
1795001561 26
1795001566 26
1795001571 26
1795001577 26
1795001582 26
1795001587 26
1795001592 51
1795001597 51
1795001602 39
1795001607 39
1795001612 39
1795001617 39
1795001622 39
1795001627 39
```
</details>

---

