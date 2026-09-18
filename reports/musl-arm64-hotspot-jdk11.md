---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:37:50 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 658 |
| Sample Rate | 10.97/sec |
| Health Score | 686% |
| Threads | 8 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 26-31 cores)</summary>

```
1789716691 31
1789716696 31
1789716701 31
1789716706 31
1789716711 31
1789716716 31
1789716721 31
1789716726 31
1789716731 31
1789716736 31
1789716741 31
1789716746 31
1789716751 31
1789716756 31
1789716761 31
1789716766 31
1789716771 31
1789716776 31
1789716781 31
1789716786 26
```
</details>

---

