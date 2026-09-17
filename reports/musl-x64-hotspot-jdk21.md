---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 16:48:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 10 |
| Allocations | 431 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 712 |
| Sample Rate | 11.87/sec |
| Health Score | 742% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1789677721 94
1789677726 94
1789677731 94
1789677736 96
1789677741 96
1789677746 96
1789677751 96
1789677756 96
1789677761 96
1789677766 96
1789677771 96
1789677776 96
1789677781 96
1789677786 96
1789677792 96
1789677797 96
1789677802 96
1789677807 96
1789677812 96
1789677817 96
```
</details>

---

