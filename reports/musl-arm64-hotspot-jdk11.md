---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 18:25:50 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
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
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 54-64 cores)</summary>

```
1792707694 54
1792707699 54
1792707704 64
1792707709 64
1792707714 64
1792707719 64
1792707724 64
1792707729 64
1792707734 64
1792707739 64
1792707744 64
1792707749 64
1792707754 64
1792707759 64
1792707764 64
1792707769 64
1792707774 64
1792707779 64
1792707784 64
1792707789 64
```
</details>

---

