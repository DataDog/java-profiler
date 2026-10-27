---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 14:34:08 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (4 unique values: 20-29 cores)</summary>

```
1793125624 20
1793125629 20
1793125634 20
1793125639 20
1793125644 20
1793125649 20
1793125654 20
1793125659 20
1793125664 25
1793125669 25
1793125674 25
1793125679 25
1793125684 25
1793125689 25
1793125694 25
1793125699 25
1793125704 25
1793125709 25
1793125714 25
1793125720 25
```
</details>

---

