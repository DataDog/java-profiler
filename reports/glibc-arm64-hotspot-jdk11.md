---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 13:05:22 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 222 |
| Sample Rate | 3.70/sec |
| Health Score | 231% |
| Threads | 11 |
| Allocations | 86 |

<details>
<summary>CPU Timeline (3 unique values: 36-52 cores)</summary>

```
1792515706 41
1792515711 41
1792515716 41
1792515721 41
1792515726 41
1792515731 41
1792515736 41
1792515741 41
1792515746 36
1792515751 36
1792515756 36
1792515761 36
1792515766 36
1792515771 36
1792515776 36
1792515781 36
1792515786 36
1792515791 36
1792515796 36
1792515801 36
```
</details>

---

