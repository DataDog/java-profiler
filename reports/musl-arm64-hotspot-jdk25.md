---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-29 00:59:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 9 |
| Allocations | 161 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 8-13 cores)</summary>

```
1790657696 8
1790657701 8
1790657706 8
1790657711 8
1790657716 8
1790657721 8
1790657726 8
1790657731 8
1790657736 8
1790657741 13
1790657746 13
1790657751 13
1790657756 13
1790657761 13
1790657766 13
1790657771 13
1790657776 13
1790657781 13
1790657786 13
1790657791 13
```
</details>

---

