---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-11 01:02:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (4 unique values: 56-66 cores)</summary>

```
1791694722 56
1791694727 58
1791694732 58
1791694737 58
1791694742 56
1791694747 56
1791694752 56
1791694757 56
1791694762 56
1791694767 56
1791694772 56
1791694777 56
1791694782 58
1791694787 58
1791694792 58
1791694797 58
1791694802 58
1791694807 58
1791694812 58
1791694817 58
```
</details>

---

