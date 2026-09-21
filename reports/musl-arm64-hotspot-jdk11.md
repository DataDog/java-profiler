---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-21 09:08:25 EDT

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 11 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1789995761 36
1789995766 36
1789995771 36
1789995776 36
1789995781 36
1789995786 36
1789995791 36
1789995796 36
1789995801 36
1789995806 36
1789995811 36
1789995816 36
1789995821 36
1789995826 36
1789995831 36
1789995836 36
1789995841 36
1789995846 36
1789995852 36
1789995857 36
```
</details>

---

