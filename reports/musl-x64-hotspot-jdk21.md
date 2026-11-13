---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 10:15:31 EST

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 665 |
| Sample Rate | 11.08/sec |
| Health Score | 692% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 906 |
| Sample Rate | 15.10/sec |
| Health Score | 944% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (4 unique values: 84-90 cores)</summary>

```
1794582731 90
1794582736 90
1794582741 90
1794582746 90
1794582751 90
1794582756 90
1794582761 90
1794582766 88
1794582771 88
1794582776 88
1794582782 88
1794582787 88
1794582792 88
1794582797 88
1794582802 88
1794582807 88
1794582812 88
1794582817 88
1794582822 88
1794582827 88
```
</details>

---

