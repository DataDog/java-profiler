---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 10:16:36 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 6 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (1 unique values: 42-42 cores)</summary>

```
1794582713 42
1794582718 42
1794582723 42
1794582728 42
1794582733 42
1794582738 42
1794582743 42
1794582748 42
1794582753 42
1794582758 42
1794582763 42
1794582768 42
1794582773 42
1794582778 42
1794582783 42
1794582788 42
1794582793 42
1794582798 42
1794582803 42
1794582808 42
```
</details>

---

