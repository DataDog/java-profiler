---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 07:55:50 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 11 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (3 unique values: 60-63 cores)</summary>

```
1794487798 63
1794487803 63
1794487808 63
1794487813 63
1794487818 63
1794487823 63
1794487828 63
1794487833 63
1794487838 63
1794487843 63
1794487848 62
1794487853 62
1794487858 60
1794487863 60
1794487868 60
1794487873 60
1794487878 60
1794487883 60
1794487888 60
1794487893 60
```
</details>

---

