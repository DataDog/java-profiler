---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 09:57:57 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 7 |
| Allocations | 26 |

<details>
<summary>CPU Timeline (2 unique values: 45-49 cores)</summary>

```
1789998741 45
1789998746 45
1789998751 45
1789998756 49
1789998761 49
1789998766 49
1789998771 49
1789998776 49
1789998781 49
1789998786 49
1789998791 49
1789998796 49
1789998801 49
1789998806 49
1789998811 49
1789998816 49
1789998821 49
1789998826 49
1789998831 49
1789998836 49
```
</details>

---

